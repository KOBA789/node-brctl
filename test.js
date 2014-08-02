var brctl = require('./build/Release/brctl');

var log = console.log.bind(console);

log(brctl.init());
log(brctl.addBridge('br0'));
log(brctl.shutdown());
