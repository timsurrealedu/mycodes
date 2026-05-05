function themeToggle() {
    document.body.classList.toggle(
        'dark-mode',
    );
    const isDark =
        document.body.classList.contains(
            'dark-mode',
        );
    localStorage.setItem(
        'theme',
        isDark ? 'dark' : 'light',
    );
}

function loadTheme() {
    if (
        localStorage.getItem(
            'theme',
        ) === 'dark'
    ) {
        document.body.classList.add(
            'dark-mode',
        );
    }
}

function toggleMenu() {
    document
        .getElementById('main-links')
        .classList.toggle('active');
    document
        .getElementById('auth-links')
        .classList.toggle('active');
}

function updateNavbar() {
    const user = JSON.parse(
        localStorage.getItem(
            'currentUser',
        ),
    );
    const authLinks =
        document.getElementById(
            'auth-links',
        );

    if (user) {
        authLinks.innerHTML = `
            <a href="Profile.html">Profile</a>
            <button onclick="logout()">Logout</button>
            <button onclick="themeToggle()">Toggle Theme</button>
        `;
    } else {
        authLinks.innerHTML = `<a href="Login.html">Login</a>
            <a href="Register.html">Register</a>
            <button onclick="themeToggle()">Toggle Theme</button>
        `;
    }
}

function logout() {
    localStorage.removeItem(
        'currentUser',
    );
    window.location.href = 'Home.html';
}

function goToExplore() {
    const user = JSON.parse(
        localStorage.getItem(
            'currentUser',
        ),
    );
    if (user) {
        window.location.href =
            'Explore.html';
    } else {
        window.location.href =
            'Login.html';
    }
}

let slideIndex = 0;
let slideInterval;

function showSlides() {
    let slides =
        document.getElementsByClassName(
            'carousel-slide',
        );
    if (slides.length === 0) return; // Exit if not on home page

    for (
        let i = 0;
        i < slides.length;
        i++
    ) {
        slides[i].classList.remove(
            'active',
        );
    }
    slideIndex++;
    if (slideIndex > slides.length) {
        slideIndex = 1;
    }
    slides[
        slideIndex - 1
    ].classList.add('active');

    slideInterval = setTimeout(
        showSlides,
        2000,
    );
    const dots =
        document.querySelectorAll(
            '.carousel-dots .dot',
        );
    dots.forEach((d, i) =>
        d.classList.toggle(
            'active',
            i === slideIndex - 1,
        ),
    );
    function jumpToSlide(n) {
        clearTimeout(slideInterval);
        slideIndex = n;
        showSlides();
    }
}

function moveSlide(n) {
    clearTimeout(slideInterval);
    let slides =
        document.getElementsByClassName(
            'carousel-slide',
        );
    slideIndex += n - 1;
    if (slideIndex < 0) {
        slideIndex = slides.length - 1;
    }
    showSlides();
}

document.addEventListener(
    'DOMContentLoaded',
    () => {
        loadTheme();
        updateNavbar();
        showSlides();
    },
);
