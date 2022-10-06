#define val_crop {if (val<sat_n) {val = sat_n; v->Limited = 1;} if (val>sat_p) {val = sat_p; v->Limited = 1;}}
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  int sat_p, sat_n, val;
  sat_p = v->Lim;
  sat_n = -v->Lim;

  v->Limited = 0;

  val = __IQ((1 + *v->k * (*v->In_r1 - 1)/2),24);
  val_crop;
  v->Out_r1_TOP = val;

  val = __IQ((-1 + *v->k * (*v->In_r1 + 1)/2),24);
  val_crop;
  v->Out_r1_BOT = val;

  val = __IQ((1 + *v->k * (*v->In_r2 - 1)/2),24);
  val_crop;
  v->Out_r2_TOP = val;

  val = __IQ((-1 + *v->k * (*v->In_r2 + 1)/2),24);
  val_crop;
  v->Out_r2_BOT = val;

  val = __IQ((1 + *v->k * (*v->In_r3 - 1)/2),24);
  val_crop;
  v->Out_r3_TOP = val;

  val = __IQ((-1 + *v->k * (*v->In_r3 + 1)/2),24);
  val_crop;
  v->Out_r3_BOT = val;
}

