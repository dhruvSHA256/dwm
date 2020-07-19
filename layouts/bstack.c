void
getfacts(Monitor *m, int msize, int ssize, float *mf, float *sf, int *mr, int *sr);

static void
bstack(Monitor *m)
{
	unsigned int i, n;
	int mx = 0, my = 0, mh = 0, mw = 0;
	int sx = 0, sy = 0, sh = 0, sw = 0;
	float mfacts, sfacts;
	int mtotal = 0, stotal = 0;
	int mrest, srest;
	Client *c;


	int oh, ov, ih, iv;
	oh = m->gappoh ;
    ov = m->gappov ;
    ih = m->gappih ;
    iv = m->gappiv ;


	if (n == 0)
		return;


	sx = mx = m->wx + ov;
	sy = my = m->wy + oh;
	sh = mh = m->wh - 2*oh;
	mw = m->ww - 2*ov - iv * (MIN(n, m->nmaster) - 1);
	sw = m->ww - 2*ov - iv * (n - m->nmaster - 1);

	if (m->nmaster && n > m->nmaster) {
		sh = (mh - ih) * (1 - m->mfact);
		mh = (mh - ih) * m->mfact;
		sx = mx;
		sy = my + mh + ih;
	}


	getfacts(m, mw, sw, &mfacts, &sfacts, &mrest, &srest);



	for (i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++) {
		if (i < m->nmaster) {
			#if CFACTS_PATCH
			resize(c, mx, my, (mw / mfacts) * c->cfact + (i < mrest ? 1 : 0) - (2*c->bw), mh - (2*c->bw), 0);
			#else
			resize(c, mx, my, (mw / mfacts) + (i < mrest ? 1 : 0) - (2*c->bw), mh - (2*c->bw), 0);
			#endif // CFACTS_PATCH
	
			mx += WIDTH(c) + iv;

		} else {
			#if CFACTS_PATCH
			resize(c, sx, sy, (sw / sfacts) * c->cfact + ((i - m->nmaster) < srest ? 1 : 0) - (2*c->bw), sh - (2*c->bw), 0);
			#else
			resize(c, sx, sy, (sw / sfacts) + ((i - m->nmaster) < srest ? 1 : 0) - (2*c->bw), sh - (2*c->bw), 0);
			#endif // CFACTS_PATCH
	
			sx += WIDTH(c) + iv;
	
		}
	}
}

void
getfacts(Monitor *m, int msize, int ssize, float *mf, float *sf, int *mr, int *sr)
{
	unsigned int n;
	float mfacts, sfacts;
	int mtotal = 0, stotal = 0;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	mfacts = MIN(n, m->nmaster);
	sfacts = n - m->nmaster;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++)
		if (n < m->nmaster)
			mtotal += msize / mfacts;
		else
			stotal += ssize / sfacts;

	*mf = mfacts; // total factor of master area
	*sf = sfacts; // total factor of stack area
	*mr = msize - mtotal; // the remainder (rest) of pixels after an even master split
	*sr = ssize - stotal; // the remainder (rest) of pixels after an even stack split
}
