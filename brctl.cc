#include <node.h>
#include <nan.h>

#include "libbridge.h"

using namespace v8;

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

  String::Utf8Value str(args[0]->ToString());

  int ret = br_add_bridge(*str);

  NanReturnValue(NanNew<Integer>(ret));
}

void init(Handle<Object> exports) {
  // exports.hello = sayHello;
  exports->Set(NanSymbol("hello"), NanNew<FunctionTemplate>(sayHello)->GetFunction());

  exports->Set(NanSymbol("init"), NanNew<FunctionTemplate>(init_)->GetFunction());
  exports->Set(NanSymbol("shutdown"), NanNew<FunctionTemplate>(shutdown)->GetFunction());
  exports->Set(NanSymbol("addBridge"), NanNew<FunctionTemplate>(addBridge)->GetFunction());
}

// module name is brctl
NODE_MODULE(brctl, init)
