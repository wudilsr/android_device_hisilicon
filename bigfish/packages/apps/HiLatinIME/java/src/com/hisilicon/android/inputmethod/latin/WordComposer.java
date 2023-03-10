/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

package com.hisilicon.android.inputmethod.latin;

import com.hisilicon.android.inputmethod.keyboard.KeyDetector;

import java.util.ArrayList;

/**
 * A place to store the currently composing word with information such as adjacent key codes as well
 */
public class WordComposer {

    public static final int NOT_A_CODE = KeyDetector.NOT_A_CODE;
    public static final int NOT_A_COORDINATE = -1;

    /**
     * The list of unicode values for each keystroke (including surrounding keys)
     */
    private ArrayList<int[]> mCodes;

    private int[] mXCoordinates;
    private int[] mYCoordinates;

    private StringBuilder mTypedWord;

    private int mCapsCount;

    private boolean mAutoCapitalized;

    /**
     * Whether the user chose to capitalize the first char of the word.
     */
    private boolean mIsFirstCharCapitalized;

    public WordComposer() {
        final int N = BinaryDictionary.MAX_WORD_LENGTH;
        mCodes = new ArrayList<int[]>(N);
        mTypedWord = new StringBuilder(N);
        mXCoordinates = new int[N];
        mYCoordinates = new int[N];
    }

    public WordComposer(WordComposer source) {
        init(source);
    }

    public void init(WordComposer source) {
        mCodes = new ArrayList<int[]>(source.mCodes);
        mTypedWord = new StringBuilder(source.mTypedWord);
        mXCoordinates = source.mXCoordinates;
        mYCoordinates = source.mYCoordinates;
        mCapsCount = source.mCapsCount;
        mIsFirstCharCapitalized = source.mIsFirstCharCapitalized;
        mAutoCapitalized = source.mAutoCapitalized;
    }

    /**
     * Clear out the keys registered so far.
     */
    public void reset() {
        mCodes.clear();
        mTypedWord.setLength(0);
        mCapsCount = 0;
        mIsFirstCharCapitalized = false;
    }

    /**
     * Number of keystrokes in the composing word.
     * @return the number of keystrokes
     */
    public final int size() {
        return mTypedWord.length();
    }

    /**
     * Returns the codes at a particular position in the word.
     * @param index the position in the word
     * @return the unicode for the pressed and surrounding keys
     */
    public int[] getCodesAt(int index) {
        return mCodes.get(index);
    }

    public int[] getXCoordinates() {
        return mXCoordinates;
    }

    public int[] getYCoordinates() {
        return mYCoordinates;
    }

    private static boolean isFirstCharCapitalized(int index, int codePoint, boolean previous) {
        if (index == 0) return Character.isUpperCase(codePoint);
        return previous && !Character.isUpperCase(codePoint);
    }

    /**
     * Add a new keystroke, with codes[0] containing the pressed key's unicode and the rest of
     * the array containing unicode for adjacent keys, sorted by reducing probability/proximity.
     * @param codes the array of unicode values
     */
    public void add(int primaryCode, int[] codes, int x, int y) {
        final int newIndex = size();
        mTypedWord.append((char) primaryCode);
        correctPrimaryJuxtapos(primaryCode, codes);
        mCodes.add(codes);
        if (newIndex < BinaryDictionary.MAX_WORD_LENGTH) {
            mXCoordinates[newIndex] = x;
            mYCoordinates[newIndex] = y;
        }
        mIsFirstCharCapitalized = isFirstCharCapitalized(
                newIndex, primaryCode, mIsFirstCharCapitalized);
        if (Character.isUpperCase(primaryCode)) mCapsCount++;
    }

    /**
     * Swaps the first and second values in the codes array if the primary code is not the first
     * value in the array but the second. This happens when the preferred key is not the key that
     * the user released the finger on.
     * @param primaryCode the preferred character
     * @param codes array of codes based on distance from touch point
     */
    private void correctPrimaryJuxtapos(int primaryCode, int[] codes) {
        if (codes.length < 2) return;
        if (codes[0] > 0 && codes[1] > 0 && codes[0] != primaryCode && codes[1] == primaryCode) {
            codes[1] = codes[0];
            codes[0] = primaryCode;
        }
    }

    /**
     * Delete the last keystroke as a result of hitting backspace.
     */
    public void deleteLast() {
        final int size = size();
        if (size > 0) {
            final int lastPos = size - 1;
            char lastChar = mTypedWord.charAt(lastPos);
            mCodes.remove(lastPos);
            mTypedWord.deleteCharAt(lastPos);
            if (Character.isUpperCase(lastChar)) mCapsCount--;
        }
        if (size() == 0) {
            mIsFirstCharCapitalized = false;
        }
    }

    /**
     * Returns the word as it was typed, without any correction applied.
     * @return the word that was typed so far
     */
    public String getTypedWord() {
        if (size() == 0) {
            return null;
        }
        return mTypedWord.toString();
    }

    /**
     * Whether or not the user typed a capital letter as the first letter in the word
     * @return capitalization preference
     */
    public boolean isFirstCharCapitalized() {
        return mIsFirstCharCapitalized;
    }

    /**
     * Whether or not all of the user typed chars are upper case
     * @return true if all user typed chars are upper case, false otherwise
     */
    public boolean isAllUpperCase() {
        return (mCapsCount > 0) && (mCapsCount == size());
    }

    /**
     * Returns true if more than one character is upper case, otherwise returns false.
     */
    public boolean isMostlyCaps() {
        return mCapsCount > 1;
    }

    /**
     * Saves the reason why the word is capitalized - whether it was automatic or
     * due to the user hitting shift in the middle of a sentence.
     * @param auto whether it was an automatic capitalization due to start of sentence
     */
    public void setAutoCapitalized(boolean auto) {
        mAutoCapitalized = auto;
    }

    /**
     * Returns whether the word was automatically capitalized.
     * @return whether the word was automatically capitalized
     */
    public boolean isAutoCapitalized() {
        return mAutoCapitalized;
    }
}
