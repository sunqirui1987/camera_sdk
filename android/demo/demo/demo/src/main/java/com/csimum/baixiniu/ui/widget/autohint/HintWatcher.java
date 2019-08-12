package com.csimum.baixiniu.ui.widget.autohint;

public abstract class HintWatcher {

    private SuffixEditText mEditText;

    public HintWatcher(SuffixEditText editText) {
        mEditText = editText;
    }

    protected int diff(String s1, String s2) {
        if (s1.length() > s2.length()) {
            return -1;
        }
        int i = 0;
        for (; i < s1.length(); i++) {
            if (s1.charAt(i) != s2.charAt(i)) {
                return -1;
            }
        }
        return i;
    }

    protected void setSuffix(String suffix) {
        if (mEditText != null) {
            mEditText.setSuffix(suffix);
        }
    }

    public abstract void check(String s);

}
