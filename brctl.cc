#include <node.h>
#include <nan.h>

using namespace v8;

// function sayHello () { return 'world'; }
NAN_METHOD(sayHello) {
  NanScope();

  NanReturnValue(NanSymbol("hello world"));
}

void init(Handle<Object> exports) {
  // exports.hello = sayHello;
  exports->Set(NanSymbol("hello"), FunctionTemplate::New(sayHello)->GetFunction());
}

// module name is brctl
NODE_MODULE(brctl, init)
