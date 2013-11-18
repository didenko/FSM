#include <CppUnitTest.h>

#include "Turnstile.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tools {
  namespace test {
    namespace fsm {

      TEST_CLASS(ToolsFsmTest) {

      public:

        TEST_METHOD(ToolsFsmCreate) {
          auto ts = Turnstile();

          Assert::AreEqual<std::string>( "locked", ts.Now(), L"Initial state expected to be 'locked'.", LINE_INFO() );
          Assert::AreEqual<unsigned long>( 0, ts.Pushed(), L"Initial push counter expected to be zero.", LINE_INFO() );
          Assert::AreEqual<unsigned long>( 0, ts.Paid(), L"Initial coin counter expected to be zero.", LINE_INFO() );
        };

        TEST_METHOD(ToolsFsmPayPush) {
          auto ts = Turnstile();

          ts( PAY );
          Assert::AreEqual<std::string>( "unlocked", ts.Now(), L"State expected to be 'unlocked' after payment.", LINE_INFO() );
          Assert::AreEqual<unsigned long>( 0, ts.Pushed(), L"Push counter expected to be zero after just payment.", LINE_INFO() );
          Assert::AreEqual<unsigned long>( 1, ts.Paid(), L"Pay counter expected to be one after one payment.", LINE_INFO() );

          ts( PUSH );
          Assert::AreEqual<std::string>( "locked", ts.Now(), L"State after PUSH after pay expected to be 'locked'.", LINE_INFO() );
          Assert::AreEqual<unsigned long>( 1, ts.Pushed(), L"Push counter after PUSH after pay expected to be one.", LINE_INFO() );
          Assert::AreEqual<unsigned long>( 1, ts.Paid(), L"Coin counter after PUSH after pay expected to be onw.", LINE_INFO() );
        };

        TEST_METHOD(ToolsFsmPush) {
          auto ts = Turnstile();

          ts( PUSH );
          Assert::AreEqual<std::string>( "locked", ts.Now(), L"State after PUSH without pay expected to be 'locked'.", LINE_INFO() );
          Assert::AreEqual<unsigned long>( 1, ts.Pushed(), L"Push counter after PUSH without pay expected to be one.", LINE_INFO() );
          Assert::AreEqual<unsigned long>( 0, ts.Paid(), L"Coin counter after PUSH without pay expected to be zero.", LINE_INFO() );
        };

        TEST_METHOD(ToolsFsmReset) {
          auto ts = Turnstile();

          ts( PUSH ); ts( PAY ); ts( PUSH ); ts( PAY ); ts( PAY ); ts( RESET );
          Assert::AreEqual<std::string>( "unlocked", ts.Now(), L"State after RESET after PAY expected to be 'unlocked'.", LINE_INFO() );
          Assert::AreEqual<unsigned long>( 0, ts.Pushed(), L"Push counter after RESET expected to be zero.", LINE_INFO() );
          Assert::AreEqual<unsigned long>( 0, ts.Paid(), L"Coin counter after RESET expected to be zero.", LINE_INFO() );
        };
      };
    }
  }
}
