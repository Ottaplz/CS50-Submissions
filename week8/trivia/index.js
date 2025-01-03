document.addEventListener('DOMContentLoaded', function() {

    // When correct answer is submitted change colour to red or green and display text
    // Checked How to solve to optimise with.innerhtml, previously had two hidden objects but aesthetically not as good
    document.querySelector('#arty').addEventListener('click', function(event) {
        let submission = document.querySelector('#submission');
        const answer = 'Artemis';
        if (submission.value.localeCompare(answer, undefined, { sensitivity: 'base' }) === 0) {
            submission.style.backgroundColor = 'lime';
            document.querySelector('#free').innerHTML = 'Correct!';
        }
        else {
            submission.style.backgroundColor = 'crimson';
            document.querySelector('#free').innerHTML = 'Incorrect.';
        }
        event.preventDefault();
    });
    // When correct button clicked change to green and change text

    let correct = document.querySelector('.correct');
    correct.addEventListener('click', function() {
        correct.style.backgroundColor = 'lime';
        document.querySelector('#multiple').innerHTML = 'Correct!';
        event.preventDefault();
    });
    // When incorrect button clicked change to red and change text
    // Checked how to solve to work out how to implement querySelectorAll correctly
    let incorrects = document.querySelectorAll('.incorrect');
    for (let i = 0; i < incorrects.length; i++)
        incorrects[i].addEventListener('click', function() {
            incorrects[i].style.backgroundColor = 'crimson';
            document.querySelector('#multiple').innerHTML = 'Incorrect.';
            event.preventDefault();
        });
});