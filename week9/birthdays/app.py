import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")



@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # acquire the variables and check to make sure they are valid
        name = request.form.get("name")
        day = request.form.get("day")
        day = int(day)
        month = request.form.get("month")
        month = int(month)
        if not name:
            return redirect("/")
        if day > 31 or day < 1:
            return redirect("/")
        if month > 12 or month < 1:
            return redirect("/")

        # put values into the db
        db.execute("INSERT INTO birthdays (name, day, month) VALUES(?, ?, ?)", name, day, month)

        return redirect("/")

    else:

        # return base page with db info
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays=birthdays)
