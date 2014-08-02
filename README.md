# node-brctl

node-brctl is a node addon that enables to create/destroy/modify virtual bridges in linux.

## Usage

```javascript
var assert = require('assert'),
    brctl = require('brctl'),
    Bridge = brctl.Bridge,
    NetIf = brctl.NetIf;

assert.deepEqual(Bridge.all(), []);

var br0 = Bridge.create('br0');

assert.deepEqual(Bridge.all(), [br0]);

var eth0 = new NetIf('eth0');

br0.addNetIf(eth0);
assert.deepEqual(br0.getNetIfs(), [eth0]);
br0.removeNetIf(eth0);
assert.deepEqual(br0.getNetIfs(), []);
br0.destroy();
assert.deepEqual(Bridge.all(), []);
```
