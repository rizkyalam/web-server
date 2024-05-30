// toggle ubah warna
var isClicked = false;

document.querySelector('button').addEventListener('click', function() {
    if (!isClicked) {
        document.querySelector('h1').style.color = 'salmon'
        isClicked = true;
    } else {
        document.querySelector('h1').style.color = 'skyblue'
        isClicked = false;
    }
});
