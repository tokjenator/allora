Pebble.addEventListener('ready', function() {
    console.log("PebbleKit JS ready!");
});
Pebble.addEventListener('showConfiguration', function() {
    var url = 'https://rawgit.com/tokjenator/allora/master/allora/config/index.html';
    console.log('Showing configuration page: ' + url);

    Pebble.openURL(url);
});
