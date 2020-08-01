void horizgrid(Monitor *m) {
  Client *c;
  unsigned int n, i;
  int mx = 0, my = 0, mh = 0, mw = 0;
  int sx = 0, sy = 0, sh = 0, sw = 0;
  int ntop;
  float mfacts = 0, sfacts = 0;
  int mrest, srest, mtotal = 0, stotal = 0;

  int oh, ov, ih, iv;
  getgaps(m, &oh, &ov, &ih, &iv, &n);
  if (n == 0)
    return;

  if (n <= 2)
    ntop = n;
  else {
    ntop = n / 2;
  }

  sx = mx = m->wx + ov;
  sy = my = m->wy + oh;
  sh = mh = m->wh - 2 * oh;
  sw = mw = m->ww - 2 * ov;

  if (n > ntop) {
    sh = (mh - ih) / 2;
    mh = mh - ih - sh;
    sy = my + mh + ih;
    mw = m->ww - 2 * ov - iv * (ntop - 1);
    sw = m->ww - 2 * ov - iv * (n - ntop - 1);
  }

/* calculate facts */
#if CFACTS_PATCH
  for (i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
    if (i < ntop)
      mfacts += c->cfact;
    else
      sfacts += c->cfact;

  for (i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
    if (i < ntop)
      mtotal += mh * (c->cfact / mfacts);
    else
      stotal += sw * (c->cfact / sfacts);
#else
  mfacts = ntop;
  sfacts = n - ntop;

  for (i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
    if (i < ntop)
      mtotal += mh / mfacts;
    else
      stotal += sw / sfacts;
#endif // CFACTS_PATCH

  mrest = mh - mtotal;
  srest = sw - stotal;

  for (i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
    if (i < ntop) {
#if CFACTS_PATCH
      resize(c, mx, my,
             mw * (c->cfact / mfacts) + (i < mrest ? 1 : 0) - (2 * c->bw),
             mh - (2 * c->bw), 0);
#else
      resize(c, mx, my, mw / mfacts + (i < mrest ? 1 : 0) - (2 * c->bw),
             mh - (2 * c->bw), 0);
#endif // CFACTS_PATCH
      mx += WIDTH(c) + iv;
    } else {
#if CFACTS_PATCH
      resize(c, sx, sy,
             sw * (c->cfact / sfacts) + ((i - ntop) < srest ? 1 : 0) -
                 (2 * c->bw),
             sh - (2 * c->bw), 0);
#else
      resize(c, sx, sy,
             sw / sfacts + ((i - ntop) < srest ? 1 : 0) - (2 * c->bw),
             sh - (2 * c->bw), 0);
#endif // CFACTS_PATCH
      sx += WIDTH(c) + iv;
    }
}
