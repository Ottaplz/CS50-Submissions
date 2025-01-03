import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash


from helpers import apology, login_required, lookup, usd


# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    # Establish dicts and variables
    sid = session["user_id"]
    owned_list = []
    # Retrieve necessary data from database
    user_raw = db.execute("SELECT * FROM users WHERE id=?", sid)
    symbols = db.execute("SELECT DISTINCT(symbol) FROM stocks WHERE user_id=?", sid)
    # Loop through unique stocks owned to determine current amount owned of each unique stock
    for row in range(len(symbols)):
        info_dict = {}
        purchases = 0
        sales = 0
        owned = 0
        purchases_raw = db.execute("SELECT AMOUNT FROM stocks WHERE user_id=? AND type=? AND symbol=?", sid, "purchase", symbols[row]["symbol"])
        for row2 in range(len(purchases_raw)):
            purchases += purchases_raw[row2]["AMOUNT"]
        sales_raw = db.execute("SELECT AMOUNT FROM stocks WHERE user_id=? AND type=? AND symbol=?", sid, "sale", symbols[row]["symbol"])
        for row3 in range(len(sales_raw)):
            sales += sales_raw[row3]["AMOUNT"]
        owned = purchases - sales
    # Add values to dictionaries then append the dictionaries to a list
        if owned > 0:
            info_dict["amount"] = owned
        symbol = symbols[row]["symbol"]
        info_dict["name"] = symbol
        lookup_raw = lookup(symbol)
        info_dict["price"] = lookup_raw["price"]
        owned_list.append(info_dict)
    return render_template("index.html", owned_list=owned_list, user_raw=user_raw)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    # User reached route via GET
    if request.method == "GET":
        return render_template("buy.html")

    # User reached route via POST (as by submitting a form via POST)
    else:
        # Recieve input from user
        symbol = request.form.get("symbol").upper()
        if not symbol:
            return apology("Please enter a stock symbol")
        # Ensure a valid stock symbol
        row = lookup(symbol)
        if row == None:
            return apology("Please enter a valid symbol")
        # Ensure a valid number of shares
        shares = request.form.get("shares")
        amount = int(shares)
        if not amount:
            return apology("Please enter a valid amount to purchase")
        if amount.isdigit() != True:
            return apology("Please enter a whole number")
        if amount < 1:
            return apology("Please enter a valid amount to purchase")
        # Ensure enough cash in account to purchase
        value = row["price"]
        total = int(value * amount)
        sid = session["user_id"]
        val = db.execute("SELECT cash FROM users WHERE id==?", sid)
        cash = val[0]["cash"]
        if total > cash:
            return apology("Not enough cash to purchase")
        cost = round(cash - total, 2)
        # Subtract from account otherwise and add purchase information to new db table
        db.execute("UPDATE users SET cash=? WHERE id=?", cost, sid)
        # Add to stocks table
        todays_date = datetime.datetime.now()
        db.execute("INSERT INTO stocks (user_id, symbol, price, amount, date, type) VALUES(?, ?, ?, ?, ?, ?)", sid, symbol, value, amount, todays_date, "purchase")

        return redirect("/")



@app.route("/history")
@login_required
def history():
    sid = session["user_id"]
    stock_row = db.execute("SELECT * FROM stocks WHERE user_id=?", sid)
    return render_template("history.html", stock_row=stock_row)



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password")

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():

    # User reached route via GET
    if request.method == "GET":
        return render_template("quote.html")

    # User reached route via POST (as by submitting a form via POST)
    else:
        # Recieve input from user
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Please enter a stock symbol")
        # Ensure a valid stock symbol
        row = lookup(symbol)
        if row == None:
            return apology("Please enter a valid symbol")
        return render_template("quoted.html", row=row)


@app.route("/register", methods=["GET", "POST"])
def register():
    # Register user for an account

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        username_check = {"username": None}
        username_check["username"] = db.execute("SELECT username FROM users WHERE username = ?", request.form.get("username"))

        # Checking to see if username is input
        if not username:
            return apology("must provide username")

        # Checking to see if password or confirmation is input
        elif not password or not confirmation:
            return apology("must provide password and/or confirmation")

        # Checking to see if password and confirmation match
        elif password != confirmation:
            return apology("password and confirmation must match")

        # Check database to see if username already exists
        elif username_check["username"] == username:
            return apology("username already exists")

        # Insert username and password into db
        else:
            password_hash = generate_password_hash(password)
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, password_hash)

        # Redirect user to /login
        return render_template("login.html")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    # User reached route via GET
    if request.method == "GET":
        sid = session["user_id"]
        symbols = db.execute("SELECT DISTINCT(symbol) FROM stocks WHERE user_id=?", sid)
        symbols_dict = {}
        symbol_list = []
        # Loop through purchases and sales to determine unique stocks held
        for row in range(len(symbols)):
            purchases = 0
            sales = 0
            owned = 0
            purchases_raw = db.execute("SELECT AMOUNT FROM stocks WHERE user_id=? AND type=? AND symbol=?", sid, "purchase", symbols[row]["symbol"])
            for row2 in range(len(purchases_raw)):
                purchases += purchases_raw[row2]["AMOUNT"]
            sales_raw = db.execute("SELECT AMOUNT FROM stocks WHERE user_id=? AND type=? AND symbol=?", sid, "sale", symbols[row]["symbol"])
            for row3 in range(len(sales_raw)):
                sales += sales_raw[row3]["AMOUNT"]
            owned = purchases - sales
        # Add values to dictionaries then append the dictionaries to a list
            if owned > 0:
                symbols_dict = symbols[row]["symbol"]
                symbol_list.append(symbols_dict)
        return render_template("sell.html", symbol_list=symbol_list)

    # User reached route via POST (as by submitting a form via POST)
    else:
        # Recieve input from user
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Please enter a stock symbol")
        # Ensure a valid stock symbol
        row = lookup(symbol)
        if row == None:
            return apology("Please enter a valid symbol")
        # Ensure a valid number of shares
        shares = request.form.get("shares")
        if not shares:
            return apology("Please enter a valid amount")
        amount = int(shares)
        if amount < 1:
            return apology("Please enter a valid amount to sell")
        # Ensure enough shares owned to sell
        sid = session["user_id"]
        bought_raw = db.execute("SELECT amount FROM stocks WHERE user_id=? AND symbol=? AND type=?", sid, symbol, "purchase")
        sold_raw = db.execute("SELECT amount FROM stocks WHERE user_id=? AND symbol=? AND type=?", sid, symbol, "sale")
        bought = 0
        sold = 0
        for row2 in range(len(bought_raw)):
            bought += bought_raw[row2]["AMOUNT"]
        for row3 in range(len(sold_raw)):
            sold += sold_raw[row3]["AMOUNT"]
        owned = bought - sold
        if amount > owned:
            return apology("Not enough shares owned to sell")
        # Add value of stocks sold to users cash total
        value = row["price"]
        total_sold = int(value * amount)
        # Add to account and add purchase information to new db table
        val = db.execute("SELECT cash FROM users WHERE id==?", sid)
        cash = val[0]["cash"]
        total = round(cash + total_sold, 2)
        db.execute("UPDATE users SET cash=? WHERE id=?", total, sid)
        # Add to stocks table
        todays_date = datetime.datetime.now()
        db.execute("INSERT INTO stocks (user_id, symbol, price, amount, date, type) VALUES(?, ?, ?, ?, ?, ?)", sid, symbol, value, amount, todays_date, "sale")

        return redirect("/")
