Pebble.addEventListener('ready', function() {
    console.log("PebbleKit JS ready!");
});
Pebble.addEventListener('showConfiguration', function() {
    var url = 'http://google.com';
    console.log('Showing configuration page: ' + url);

    Pebble.openURL(url);
});
