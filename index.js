var brctlBinding = require('./build/Release/brctl'),
    assert = require('assert'),
    errno = require('errno').errno;

brctlBinding.init_();

var brctl = module.exports = {};

function Bridge (brname) {
  assert.strictEqual(typeof brname, 'string');
  this._brname = brname;
}

Bridge.create = function (brname) {
  assert.strictEqual(typeof brname, 'string');

  var ret = brctlBinding.addBridge(brname);
  if (ret === 0) {
    return new Bridge(brname);
  } else {
    throw new Error(error(ret));
  }
};

Bridge.prototype.remove = function () {
  assert.strictEqual(typeof this._brname, 'string');
  var ret = brctlBinding.deleteBridge(this._brname);
  if (ret === 0) {
    return new Bridge(this._brname);
  } else {
    throw new Error(error(ret));
  }
};

Bridge.all = function () {
  return brctlBinding.getBridges().map(function (brname) {
    return new Bridge(brname);
  });
};

Bridge.prototype.getPorts = function () {
  assert.strictEqual(typeof this._brname, 'string');
  return brctlBinding.getPorts(this._brname).map(function (ifname) {
    return new NetworkInterface(ifname);
  });  
};

Bridge.prototype.getName = function () {
  assert.strictEqual(typeof this._brname, 'string');
  return this._brname;
};

Bridge.prototype.toString = function () {
  assert.strictEqual(typeof this._brname, 'string');
  return ['[', this._brname, ' Brigde]'].join('');
};

function NetworkInterface (ifname) {
  assert.strictEqual(typeof ifname, 'string');
  this._ifname = ifname;
}

NetworkInterface.prototype.getName = function () {
  assert.strictEqual(typeof this._ifname, 'string');
  return this._ifname;
};

NetworkInterface.prototype.toString = function () {
  assert.strictEqual(typeof this._ifname, 'string');
  return ['[', this._ifname, ' NetworkInterface]'].join('');
};

function error (no) {
  var descObj = (errno[no] || errno[-1]);
  return [
    descObj.code,
    '(', descObj.errno, '): ',
    descObj.description
  ].join('');
}

brctl.createBridge = function (brname) {
  return Bridge.create(brname);
};

brctl.shutdown = function () {
  brctlBinding.shutdown();
};

brctl.Bridge = Bridge;
brctl.NetworkInterface = NetworkInterface;
