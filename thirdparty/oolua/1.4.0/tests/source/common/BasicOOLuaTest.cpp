#include <oolua.h>
#include <gtest/gtest.h>

class TestOOLua : public testing::Test
{
};

TEST_F(TestOOLua, BasicTest)  // NOLINT
{
    OOLUA::Script* lScript;
    lScript = new OOLUA::Script;
    lScript->run_chunk("test = function() "
                     "print (\"Hello world!\") "
                     "end ");
    bool result = lScript->call("test");
    delete lScript;
    ASSERT_TRUE(result);
}

struct foo
{
  int bar();
};

OOLUA_CLASS_NO_BASES(foo)  //class has no bases
    OOLUA_NO_TYPEDEFS
    OOLUA_ONLY_DEFAULT_CONSTRUCTOR
    OOLUA_MEM_FUNC_0(int/*return type*/
                   ,bar/*function name*/)
OOLUA_CLASS_END

EXPORT_OOLUA_FUNCTIONS_1_NON_CONST(foo /*name of class*/
                                  ,bar)/*function being exposed*/
EXPORT_OOLUA_FUNCTIONS_0_CONST(foo)
    
int foo::bar()
{
    return 100;
}

TEST_F(TestOOLua, CallFunc)  // NOLINT
{
    OOLUA::Script* lScript;
    lScript = new OOLUA::Script;
    lScript->register_class<foo>();
    lScript->run_chunk("test = function(obj) "
                     "print (\"Value: \" .. obj:bar() .. \"!\") "
                     "end ");
    foo sinstance;
    foo* instance = &sinstance;
    bool result = lScript->call("test", instance);
    delete lScript;
    ASSERT_TRUE(result);
}
