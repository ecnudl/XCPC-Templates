ll l, r;
while(l < r) {
 ll lmid = l + (r - l) / 3;
 ll rmid = r - (r - l) / 3;
 if(calc(lmid) <= calc(rmid))	l = lmid + 1;
 else r = rmid - 1;
}
printf("%lld\n", max(calc(l), calc(r)));

ll l, r;
while(l < r) {
 ll lmid = l + (r - l) / 3;
 ll rmid = r - (r - l) / 3;
 if(calc(rmid) >= calc(lmid))	r = rmid - 1;
 else 	l = lmid + 1;
}
printf("%lld\n", min(calc(l), calc(r)));

double l, r;
for(int i = 0; i < 300; i++) {
 double lmid = l + (r - l) / 3;
 double rmid = r - (r - l) / 3;
 if(calc(lmid) <= calc(rmid))	l = lmid;
 else 	r = rmid;
}
printf("%.6f\n", calc(l));

double l, r;
for(int i = 0; i < 300; i++) {
 double lmid = l + (r - l) / 3;
 double rmid = r - (r - l) / 3;
 if(calc(rmid) >= calc(lmid))	r = rmid;
 else 	l = lmid;
}
printf("%.6f\n", calc(l));