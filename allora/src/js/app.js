
Pebble.addEventListener('ready', function() {
    console.log("PebbleKit JS ready!");
    Pebble.sendAppMessage({'JSReady': 1});
});

Pebble.addEventListener('showConfiguration', function() {
    var url = 'https://rawgit.com/tokjenator/allora/master/allora/config/index.html';
    console.log('Showing configuration page: ' + url);

    Pebble.openURL(url);
});

Pebble.addEventListener('getDecks', function() {

});

Pebble.addEventListener('getDeckInfo', function(deckId) {

});

Pebble.addEventListener('getCardFromDeck', function(deckId, cardId) {

});

