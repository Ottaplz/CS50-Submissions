document.addEventListener('DOMContentLoaded', function() {

    var currentImage = document.getElementById("current-image");

    // Loop through all images in album and append to thumbs
    // Referenced from https://www.makeuseof.com/image-gallery-html-css-javascript/
    var imageThumbs = document.getElementById("image-thumbs");
    for (var i = 1; i <= 7; i++) {
        var thumb = document.createElement("img");
        thumb.src = "assets/album/jp-" + i + ".jpg";
        thumb.alt = "jp-" + i;
        thumb.classList.add("thumb");
        imageThumbs.appendChild(thumb);
        thumb.addEventListener(
            "click", function() {
                currentImage.src = this.src;
                currentImage.alt = this.alt;
            }
          );
    }

});