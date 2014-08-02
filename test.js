var brctl = require('./build/Release/brctl'),
    assert = require('assert');

var log = console.log.bind(console);

assert(brctl.init_() === 0);
assert(brctl.addBridge('br0') === 0);
assert(brctl.addInterface('br0', 'eth0') === 0);
assert(brctl.deleteInterface('br0', 'eth0') === 0);
assert(brctl.deleteBridge('br0') === 0);
assert(brctl.shutdown() === undefined);
