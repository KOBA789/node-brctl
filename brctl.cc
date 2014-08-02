#include <node.h>
#include <nan.h>

#include "libbridge.h"

using namespace v8;

#define STATIC_METHOD(name) exports->Set(NanNew<String>(#name), NanNew<FunctionTemplate>(name)->GetFunction())

// function sayHello () { return 'world'; }
NAN_METHOD(sayHello) {
  NanScope();

  br_hello();

  NanReturnValue(NanSymbol("hello world"));
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

  NanReturnValue(NanNew<Integer>(ret));xs
}

NAN_METHOD(deleteInterface) {
  NanScope();

  String::Utf8Value brname(args[0]->ToString());
  String::Utf8Value ifname(args[1]->ToString());

  int ret = br_del_interface(*brname, *ifname);

  NanReturnValue(NanNew<Integer>(ret));
}

void init(Handle<Object> exports) {
  STATIC_METHOD(sayHello);
  STATIC_METHOD(init_);
  STATIC_METHOD(shutdown);
  STATIC_METHOD(addBridge);
  STATIC_METHOD(deleteBridge);
  STATIC_METHOD(addInterface);
  STATIC_METHOD(deleteInterface);
}

// module name is brctl
NODE_MODULE(brctl, init)
