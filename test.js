var brctl = require('./build/Release/brctl'),
    assert = require('assert');

var log = console.log.bind(console);

try {
  assert(brctl.init_() === 0);
  assert(brctl.addBridge('br0') === 0);
  assert(brctl.addBridge('br1') === 0);
  assert(brctl.addBridge('br2') === 0);
  assert.deepEqual(brctl.getBridges(), ['br0', 'br1', 'br2']);
  assert(brctl.addInterface('br0', 'eth0') === 0);
  assert.deepEqual(brctl.getPorts('br0'), ['eth0']);
  assert(brctl.deleteInterface('br0', 'eth0') === 0);
} catch (err) {
  console.error(err);
} finally {
  assert(brctl.deleteBridge('br0') === 0);
  assert(brctl.deleteBridge('br1') === 0);
  assert(brctl.deleteBridge('br2') === 0);
  assert(brctl.shutdown() === undefined);
}
