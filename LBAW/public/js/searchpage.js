let searchInput = document.getElementById('search_input');

let categoryButtons = document.querySelectorAll('.category-link');
[...categoryButtons].forEach(button => button.addEventListener('click', (event) => {
    window.location.replace("/search?q=" + searchInput.value + "&category=" + ((button.classList.contains("selected"))? "" : button.innerHTML));
}));