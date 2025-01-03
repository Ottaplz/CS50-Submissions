document.addEventListener('DOMContentLoaded', function() {

    // Loop to check all hidden objects and then set to visible
    let objs = document.querySelectorAll('.hide');

    for (let i = 0; i < objs.length; i++)
        document.querySelector('.reveal').addEventListener('click', function() {
            objs[i].style.visibility = 'visible';
            event.preventDefault();
        })

});