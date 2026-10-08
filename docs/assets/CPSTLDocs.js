(function() {
    const page = window.location.pathname.split('/').pop();
    if (['annotated.html', 'topics.html'].includes(page) && typeof dynsection !== 'undefined') {
        dynsection.toggleLevel(2);
    }
})();
