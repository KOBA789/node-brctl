#include <node.h>
#include <nan.h>

#include <vector>

#include "libbridge.h"

using namespace v8;

#define STATIC_METHOD(name) exports->Set(NanNew<String>(#name), NanNew<FunctionTemplate>(name)->GetFunction())

// function sayHello () { return 'world'; }
NAN_METHOD(sayHello) {
  NanScope();

  br_hello();

  NanReturnValue(NanNew<String>("hello world"));
}

NAN_METHOD(init_) {
  NanScope();

  int ret = br_init();

  NanReturnValue(NanNew<Integer>(ret));
}

NAN_METHOD(shutdown) {
  NanScope();

  br_shutdown();

  NanReturnUndefined();
}

NAN_METHOD(addBridge) {
  NanScope();

  String::Utf8Value brname(args[0]->ToString());

  int ret = br_add_bridge(*brname);

  NanReturnValue(NanNew<Integer>(ret));
}

NAN_METHOD(deleteBridge) {
  NanScope();

  String::Utf8Value brname(args[0]->ToString());

  int ret = br_del_bridge(*brname);

  NanReturnValue(NanNew<Integer>(ret));
}

NAN_METHOD(addInterface) {
  NanScope();

  String::Utf8Value brname(args[0]->ToString());
  String::Utf8Value ifname(args[1]->ToString());

  int ret = br_add_interface(*brname, *ifname);

  NanReturnValue(NanNew<Integer>(ret));
}

NAN_METHOD(deleteInterface) {
  NanScope();

  String::Utf8Value brname(args[0]->ToString());
  String::Utf8Value ifname(args[1]->ToString());

  int ret = br_del_interface(*brname, *ifname);

  NanReturnValue(NanNew<Integer>(ret));
}

// working list
// (this is thread unsafe although node.js is single thread)
std::vector<Local<String>> list;
int brIterFn (const char *brname, void *arg) {
  list.push_back(NanNew<String>(brname));
}

int portIterFn (const char *brname, const char *port, void *arg) {
  list.push_back(NanNew<String>(port));
}

NAN_METHOD(getBridges) {
  NanScope();

  list.clear();
  br_foreach_bridge(brIterFn, NULL);

  Local<Array> ret = NanNew<Array>(list.size());
  int i = 0;
  for (std::vector<Local<String>>::iterator iter = list.begin(); iter != list.end(); ++iter) {
    ret->Set(i++, *iter);
  }
  list.clear();

  NanReturnValue(ret);
}

NAN_METHOD(getPorts) {
  NanScope();

  String::Utf8Value brname(args[0]->ToString());

  list.clear();
  br_foreach_port(*brname, portIterFn, NULL);

  Local<Array> ret = NanNew<Array>(list.size());
  int i = 0;
  for (std::vector<Local<String>>::iterator iter = list.begin(); iter != list.end(); ++iter) {
    ret->Set(i++, *iter);
  }
  list.clear();

  NanReturnValue(ret);
}

void init(Handle<Object> exports) {
  STATIC_METHOD(sayHello);
  STATIC_METHOD(init_);
  STATIC_METHOD(shutdown);
  STATIC_METHOD(addBridge);
  STATIC_METHOD(deleteBridge);
  STATIC_METHOD(addInterface);
  STATIC_METHOD(deleteInterface);
  STATIC_METHOD(getBridges);
  STATIC_METHOD(getPorts);
}

// module name is brctl
NODE_MODULE(brctl, init)
