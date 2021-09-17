#include "gmock/gmock.h"
#include "Soundex.h"

class SoundexEncoding : public testing::Test{
	public:
		Soundex soundex;
};

using ::testing::Eq;
using ::testing::StartsWith;

TEST_F(SoundexEncoding,DISABLED_RetainSoleLetterOfOneLetterWord)
{
	auto encoded = soundex.encode("A");
	ASSERT_THAT(encoded, Eq("A"));//给定一个字母，encode方法能正确返回吗
}
TEST_F(SoundexEncoding,PadsWithZerosToEnsureThreeDigits)
{
	auto encoded = soundex.encode("I");
	ASSERT_THAT(encoded,Eq("I000"));
}
TEST_F(SoundexEncoding,RetainSoleLetterOfOneLetterWord2)
{
	ASSERT_THAT(soundex.encode("Ab"),Eq("A100"));
}
TEST_F(SoundexEncoding,ReplacesConsonantsWithAppropriateDigits)
{
	//EXPECT_THAT(soundex.encode("Ab"),Eq("A100"));
	//EXPECT_THAT(soundex.encode("Ac"),Eq("A200"));
	//EXPECT_THAT(soundex.encode("Ad"),Eq("A300"));
	ASSERT_THAT(soundex.encode("Ax"),Eq("A200"));
}
TEST_F(SoundexEncoding,IgnoresNonAlphabetics)
{
	ASSERT_THAT(soundex.encode("A#"),Eq("A000"));
}

TEST_F(SoundexEncoding,ReplacesMultipleConsonantsWithDigits)
{
	ASSERT_THAT(soundex.encode("Acdl"),Eq("A234"));
}
TEST_F(SoundexEncoding,LimitsLengthToFourCharacters)
{
	ASSERT_THAT(soundex.encode("Dcdlb").length(),Eq(4u));
}
TEST_F(SoundexEncoding, IgnoredVowelLikeLetters)
{
	ASSERT_THAT(soundex.encode("BaAeEiIoOuUhHyYcdl"),Eq("B234"));
}
TEST_F(SoundexEncoding,CombinesDuplicateEncodings)
{
	ASSERT_THAT(soundex.encodedDigit('b'),Eq(soundex.encodedDigit('f')));
	ASSERT_THAT(soundex.encodedDigit('c'),Eq(soundex.encodedDigit('g')));
	ASSERT_THAT(soundex.encodedDigit('d'),Eq(soundex.encodedDigit('t')));
	ASSERT_THAT(soundex.encode("Abfcgdt"),Eq("A123"));
}
TEST_F(SoundexEncoding,UppercaseFirstLetter)
{
	ASSERT_THAT(soundex.encode("abcd"),StartsWith("A"));
}
TEST_F(SoundexEncoding,IgnoresCaseWhenEncodingConsonants)
{
	ASSERT_THAT(soundex.encode("BCDL"),Eq(soundex.encode("Bcdl")));
}
TEST_F(SoundexEncoding,CombinesDuplicateCodesWhen2ndLetterDuplicates1st)
{
	ASSERT_THAT(soundex.encode("Bbcd"),Eq("B230"));
}

