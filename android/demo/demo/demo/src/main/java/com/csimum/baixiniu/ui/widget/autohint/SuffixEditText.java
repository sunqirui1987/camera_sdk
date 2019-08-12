package com.csimum.baixiniu.ui.widget.autohint;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Rect;
import android.support.annotation.ColorInt;
import android.util.AttributeSet;
import android.view.View;

public class SuffixEditText extends android.support.v7.widget.AppCompatEditText {

    private int mSuffixTextColor;
    private String mSuffix = "";
    private Rect rectClip;

    public SuffixEditText(Context context) {
        super(context);
    }

    public SuffixEditText(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public SuffixEditText(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    public void setSuffixTextColor(@ColorInt int suffixTextColor) {
        mSuffixTextColor = suffixTextColor;
    }

    public void setSuffix(String suffix) {
        mSuffix = suffix;
        invalidate();
    }


    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        if (mSuffix != null && getText().length() > 0) {
            Paint mPaintSuffix = getPaint();
            if (mSuffixTextColor != 0) {
                mPaintSuffix.setColor(mSuffixTextColor);
            }
            if (rectClip == null) {
                rectClip = new Rect();
            }
            int lineBaseline = getLineBounds(0, null);
            canvas.getClipBounds(rectClip);
            float x = getPaint().measureText(getText().toString()) + getPaddingLeft();
            canvas.drawText(mSuffix, x, rectClip.top + lineBaseline, mPaintSuffix);

        }
    }
}
