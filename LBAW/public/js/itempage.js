let editCommentButtons = document.getElementsByClassName('edit_comment');
[...editCommentButtons].forEach(button => button.addEventListener('click', (event) => {
    editComment(button);
}));
let deleteCommentButtons = document.getElementsByClassName('delete_comment');
[...deleteCommentButtons].forEach(button => button.addEventListener('click', (event) => {
    deleteComment(button);
}));

let createCommentButton = document.getElementsByClassName('create_comment')[0];
createCommentButton.addEventListener('click', (event) => { createComment(createCommentButton)});

let beingEdited = false;
let beingCreated = false;

function editComment(button) {

    if (beingEdited == false) {
        button.className = "btn save_comment";
        button.innerHTML = "Save Comment";
        button.style.display = "block";
        let content = document.querySelector('.save_comment').parentElement.children[3];
        content.contentEditable = "true";
        content.focus = "true";
        content.style.padding = "0.5em";
        content.style.border = "1.5px solid gray";
        content.parentElement.style.opacity = "1";
        beingEdited = true;
        return;
    }
    if (beingEdited == true) {
        if (button.className == "edit_comment") {
            alert("Only one comment can be edited at a time!");
            return;
        }
        let content = document.querySelector('.save_comment').parentElement.children[3];
        var someText = content.innerText.replace(/(\r\n|\n|\r)/gm, "");
        if (someText.trim() == "") {
            alert("Comment cannot be left empty!");
            return;
        }
        content.innerText = content.innerText.trim();
        button.parentElement.children[button.parentElement.children.length - 2].children[1].value = content.innerText;
        button.parentElement.children[button.parentElement.children.length - 2].children[2].click();
    }
}

function deleteComment(button) {
    button.parentElement.children[button.parentElement.children.length - 1][1].click();
}

function createComment(button) {

    if (beingCreated == false) {
        let newComment = document.querySelector('#newComment');
        for (let i = 0; i < newComment.children.length; i++) {
            newComment.children[i].style.display = "block";
        }
        button.innerHTML = "Post Comment";
        let content = document.querySelector('.create_comment ~ p');
        content.contentEditable = "true";
        content.focus = "true";
        content.style.padding = "0.5em";
        content.style.border = "1.5px solid gray";
        content.parentElement.style.opacity = "1";
        beingCreated = true;
        return;
    }

    if (beingCreated == true) {
        let content = document.querySelector('.create_comment ~ p');
        var someText = content.innerText.replace(/(\r\n|\n|\r)/gm, "");
        if (someText.trim() == "") {
            alert("Comment cannot be left empty!");
            return;
        }
        content.innerText = content.innerText.trim();
        button.parentElement.children[button.parentElement.children.length - 1].children[3].value = content.innerText;
        button.parentElement.children[button.parentElement.children.length - 1].children[4].click();
    }
}

let principalImage = document.getElementById('image-principal');
let imagesButtons = document.querySelectorAll('.image-square > img');
[...imagesButtons].forEach(button => button.addEventListener('click', (event) => {
    console.log(principalImage.src);
    principalImage.src = button.src
    console.log(principalImage.src);
}));