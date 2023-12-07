if (!decodeData(&s, &dataType,
        &format, &version)
    && (format != 2U)    /* expecting only format 2 */
    && (version != 1U))  /* expecting only version 1 */
{
    log("data corrupt");
}

if (x < 0) {
    z = 25;
}
if (--cnt == 0) {
    z = 10;
    cnt = 1000;
}
else {
    z = 200;
}
if (x > y) {
    foo(x, y);
    z = 100;
}
else {
    if (y < x) {
        foo(y, x);
        z = 200;
    }
    else {
        x = 0;
        y = 0;
    }
}

for (i = 0; i < MAX_ITER; ++i) {
    *p2++ = *p1++;
    xx[i] = 0;
}

while (--ctr != 0) {
    *p2++ = *p1++;
    *p3++ = 0;
}

do {
    --ctr;
    *p2++ = *p1++;
} while (cnt > 0);

switch (key) {
    case KEY_BS: {
        if (--me->ctr == 0) {
            me->ctr = PERIOD;
        }
        break;
    }
    case KEY_CR: {
        ++me->crCtr;
        /* intentionally fall through */
    }
    case KEY_LF: {
        ++p;
        break;
    }
    default: {
        Q_ERROR(); /* should never be reached */
        break;
    }
}

void clrBuf(char *buf[], int len) {
    char *b = &buf[0];
    while (len-- != 0) {
        *b++ = '\0';
    }
}
