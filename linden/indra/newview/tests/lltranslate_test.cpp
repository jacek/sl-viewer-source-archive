/**
* @file lltranslate_test.cpp
* @brief Tests LLTranslate which translates between human languages.
*
* $LicenseInfo:firstyear=2009&license=viewergpl$
*
* Copyright (c) 2009, Linden Research, Inc.
*
* Second Life Viewer Source Code
* The source code in this file ("Source Code") is provided by Linden Lab
* to you under the terms of the GNU General Public License, version 2.0
* ("GPL"), unless you have obtained a separate licensing agreement
* ("Other License"), formally executed by you and Linden Lab. Terms of
* the GPL can be found in doc/GPL-license.txt in this distribution, or
* online at http://secondlifegrid.net/programs/open_source/licensing/gplv2
*
* There are special exceptions to the terms and conditions of the GPL as
* it is applied to this Source Code. View the full text of the exception
* in the file doc/FLOSS-exception.txt in this software distribution, or
* online at
* http://secondlifegrid.net/programs/open_source/licensing/flossexception
*
* By copying, modifying or distributing this software, you acknowledge
* that you have read and understood your obligations described above,
* and agree to abide by those obligations.
*
* ALL LINDEN LAB SOURCE CODE IS PROVIDED "AS IS." LINDEN LAB MAKES NO
* WARRANTIES, EXPRESS, IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY,
* COMPLETENESS OR PERFORMANCE.
* $/LicenseInfo$
*/
#include "../test/lltut.h"
#include "../lltranslate.h"

#include "llerror.h"
#include "llsdhttpserver.h"
#include "lliohttpserver.h"
#include "llhttpclient.h"
#include "indra_constants.h"

namespace tut
{
	struct TranslateTestData
	{
	public:
		TranslateTestData()
		{
			apr_pool_create(&mPool, NULL);
			mServerPump = new LLPumpIO(mPool);
			mClientPump = new LLPumpIO(mPool);

			LLHTTPClient::setPump(*mClientPump);
		}

		~TranslateTestData()
		{
			delete mServerPump;
			delete mClientPump;
			apr_pool_destroy(mPool);
		}

		void setupTheServer()
		{
			LLHTTPNode& root = LLIOHTTPServer::create(mPool, *mServerPump, 8888);

			LLHTTPStandardServices::useServices();
			LLHTTPRegistrar::buildAllServices(root);
		}

		void runThePump(float timeout = 100.0f)
		{
			LLTimer timer;
			timer.setTimerExpirySec(timeout);			
			
			while(!mSawCompleted && !timer.hasExpired())
			{
				if (mServerPump)
				{
					mServerPump->pump();
					mServerPump->callback();
				}
				if (mClientPump)
				{
					mClientPump->pump();
					mClientPump->callback();
				}
			}
		}

		void killServer()
		{
			delete mServerPump;
			mServerPump = NULL;
		}

	private:
		apr_pool_t* mPool;
		LLPumpIO* mServerPump;
		LLPumpIO* mClientPump;

	protected:
		void ensureStatusOK()
		{
			if (mSawError)
			{
				std::string msg =
					llformat("error() called when not expected, status %d",
					mStatus);
				fail(msg);
			}
		}

		void ensureStatusError()
		{
			if (!mSawError)
			{
				fail("error() wasn't called");
			}
		}

		std::string getResult()
		{
			return mResult;
		}

	protected:
		bool mSawError;
		U32 mStatus;
		std::string mReason;
		bool mSawCompleted;
		std::string mResult;
		bool mResultDeleted;

		class TranslationTestReceiver: public LLTranslate::TranslationReceiver
		{
		public:
			TranslationTestReceiver(const std::string &fromLang, const std::string &toLang,
				const std::string &mesg, TranslateTestData &translationData)
				: LLTranslate::TranslationReceiver(fromLang, toLang, mesg),
				mClient(translationData)
			{
			}

			~TranslationTestReceiver()
			{
				mClient.mResultDeleted = true;
			}

			virtual void error(U32 status, const std::string& reason)
			{
				mClient.mSawError = true;
				mClient.mStatus = status;
				mClient.mReason = reason;
			}

			static boost::intrusive_ptr<TranslationTestReceiver> build(const std::string &fromLang, const std::string &toLang,
				const std::string &mesg, TranslateTestData &translationData)
			{
				return boost::intrusive_ptr<TranslationTestReceiver>(new TranslationTestReceiver(fromLang, toLang, mesg, translationData));
			}

		protected:
			void handleResponse(const std::string &translation, const std::string &detectedLanguage)
			{
				std::string fromLang = (detectedLanguage.length() > 0 ? detectedLanguage : m_fromLang);
				LL_INFOS("Translate") << "Translation : " << translation << " (" <<
					fromLang << ")" << LL_ENDL;

				mClient.mSawCompleted = true;
				mClient.mResult = translation;
			}
		private:
			TranslateTestData& mClient;
		};

		friend class TranslationTestReceiver;

	protected:
		LLHTTPClient::ResponderPtr newResult(const std::string &fromLang, const std::string &toLang, const std::string &mesg)
		{
			mSawError = false;
			mStatus = 0;
			mSawCompleted = false;
			mResultDeleted = false;

			return TranslationTestReceiver::build(fromLang, toLang, mesg, *this);
		}
	};

	typedef test_group<TranslateTestData> TranslateTestGroup;
	typedef TranslateTestGroup::object TranslateTestObject;
	TranslateTestGroup translateTestGroup("translate");

	// Test translation requests aren't throwing an error
	template<> template<>
	void TranslateTestObject::test<1>()
	{
		std::string fromLang = "en";
		std::string toLang = "es";
		std::string mesg = "Hello!";

		setupTheServer();
		LLTranslate::translateMessage(newResult(fromLang, toLang, mesg), fromLang, toLang, mesg);
		runThePump();

		ensureStatusOK();
	}

	// Test whether we get a translation back
	template<> template<>
	void TranslateTestObject::test<2>()
	{
		std::string fromLang = "en";
		std::string toLang = "es";
		std::string mesg = "Hello!";

		setupTheServer();
		LLTranslate::translateMessage(newResult(fromLang, toLang, mesg), fromLang, toLang, mesg);
		runThePump();

		ensureStatusOK();
		ensure("Translation from English 'Hello!' to Spanish failed, empty string returned",
			getResult().length() > 0);
	}

	// Test for a correct translation of an ASCII language
	template<> template<>
	void TranslateTestObject::test<3>()
	{
		std::string fromLang = "en";
		std::string toLang = "es";
		std::string mesg = "Hello!";

		setupTheServer();
		LLTranslate::translateMessage(newResult(fromLang, toLang, mesg), fromLang, toLang, mesg);
		runThePump();
		ensureStatusOK();

		ensure("Translation from English 'Hello!' to Spanish failed, expected 'Hola'",
			getResult() == "Hola!");
	}

	// Test sending multiple requests simultaneously
	template<> template<>
	void TranslateTestObject::test<4>()
	{
		setupTheServer();
		char buff[32];
		for (int i = 0; i < 5; i++)
		{
			std::string fromLang = "en";
			std::string toLang = "es";
			sprintf(buff, "Hello %d!", i);
			std::string mesg = buff;

			LLTranslate::translateMessage(newResult(fromLang, toLang, mesg), fromLang, toLang, mesg);
			runThePump();
			ensureStatusOK();
		}
	}

	// Test 'translating' symbols that may need escaping
	template<> template<>
	void TranslateTestObject::test<5>()
	{
		std::string fromLang = "en";
		std::string toLang = "en";
		std::string mesg = ".?<>,/=&!@#$%^*()-_+[]{};:'\"\\|~`";

		setupTheServer();

		for (unsigned int i = 0; i < mesg.length(); i++)
		{
			char c = mesg.at(i);
			std::stringstream ss;
			std::string s;
			ss << c;
			ss >> s;
			LLTranslate::translateMessage(newResult(fromLang, toLang, s), fromLang, toLang, s);
			runThePump();

			ensureStatusOK();
			std::string error = "Translation of symbol '" + s + "' failed, returned '" + getResult() + "'";
			ensure(error, getResult().compare(s) == 0);
		}
	}

	// Test for the correct sending of non ascii languages,
	// this depends on having a User-Agent header in the URL request
	template<> template<>
	void TranslateTestObject::test<6>()
	{
		std::string fromLang = "ja";
		std::string toLang = "en";
		std::string mesg = "木";

		setupTheServer();
		LLTranslate::translateMessage(newResult(fromLang, toLang, mesg), fromLang, toLang, mesg);
		runThePump();

		ensureStatusOK();
		ensure("Translation of non-ascii text failed (Japanese->English) .. expected 'Tree'", getResult() == "Tree");
	}

	// Test for automatic recognition of a non-ASCII language
	template<> template<>
	void TranslateTestObject::test<7>()
	{
		std::string fromLang = "";
		std::string toLang = "en";
		std::string mesg = "木";

		setupTheServer();
		LLTranslate::translateMessage(newResult(fromLang, toLang, mesg), fromLang, toLang, mesg);
		runThePump();

		ensureStatusOK();
		ensure("Translation of non-ascii text failed (Automatic->English) .. expected 'Tree'", getResult() == "Tree");
	}

	// Test for automatic translation to a non-ASCII language
	template<> template<>
	void TranslateTestObject::test<8>()
	{
		std::string fromLang = "";
		std::string toLang = "ja";
		std::string mesg = "Tree";

		setupTheServer();
		LLTranslate::translateMessage(newResult(fromLang, toLang, mesg), fromLang, toLang, mesg);
		runThePump();

		ensureStatusOK();
		ensure("Translation to non-ascii text failed (Automatic->Japanese) .. expected '木'", getResult() == "木");
	}
}
