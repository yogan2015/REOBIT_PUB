static void U_Check (BLOCK_STRUCT *v,  int Check)
{
  long *U = &v->U1;
  long *t = &v->t1;
  long Per;
  long pPercent;
  long k;
  long b;
  long pk;
  long pb;
  long pT;

  switch(Check)
  {
    case 0:
    if (*v-> Mode == 1)
    {
      Per = _IQ16(0.18);
    }
    else if (*v-> Mode == 2)
    {
      Per = _IQ16(0.82);
    }
    break;

    case 1:
    if (*v-> Mode == 1)
    {
      Per = _IQ16(0.33);
    }
    else if (*v-> Mode == 2)
    {
      Per = _IQ16(0.67);
    }
    break;

    case 2:
    if (*v-> Mode == 1)
    {
      Per = _IQ16(0.45);
    }
    else if (*v-> Mode == 2)
    {
      Per = _IQ16(0.55);
    }
    break;

    case 3:
    if (*v-> Mode == 1)
    {
      Per = _IQ16(0.55);
    }
    else if (*v-> Mode == 2)
    {
      Per = _IQ16(0.45);
    }
    break;

    case 4:
    if (*v-> Mode == 1)
    {
      Per = _IQ16(0.63);
    }
    else if (*v-> Mode == 2)
    {
      Per = _IQ16(0.37);
    }
    break;

    case 5:
    if (*v-> Mode == 1)
    {
      Per = _IQ16(0.736);
    }
    else if (*v-> Mode == 2)
    {
      Per = _IQ16(0.264);
    }
    break;

    case 6:
    if (*v-> Mode == 1)
    {
      Per = _IQ16(0.81);
    }
    else if (*v-> Mode == 2)
    {
      Per = _IQ16(0.19);
    }
    break;

    case 7:
    if (*v-> Mode == 1)
    {
      Per = _IQ16(0.865);
    }
    else if (*v-> Mode == 2)
    {
      Per = _IQ16(0.135);
    }
    break;

    case 8:
    if (*v-> Mode == 1)
    {
      Per = _IQ16(0.918);
    }
    else if (*v-> Mode == 2)
    {
      Per = _IQ16(0.082);
    }
    break;

    case 9:
    if (*v-> Mode == 1)
    {
      Per = _IQ16(0.95);
    }
    else if (*v-> Mode == 2)
    {
      Per = _IQ16(0.05);
    }
    break;
  }

    pk = _IQ16div(U[Check - 1] - U[Check], _IQtoIQ(t[Check - 1] - t[Check], 24, 16));
    pb = _IQ16div(_IQ16mpyIQX(t[Check - 1], 24, U[Check], 16) - _IQ16mpyIQX(t[Check], 24, U[Check - 1], 16), _IQtoIQ(t[Check - 1] - t[Check], 24, 16));
  if (*v->Mode == 2)
    {
    pT = _IQ16div(_IQ16mpy(Per, (v-> pUcharge)) - pb, pk);
    }
    else
    {
    pT = _IQ16div(_IQ16mpy(Per, (*v->Urst - v-> pUcharge)) + v-> pUcharge - pb, pk);
    }

    pPercent = _IQ16div( ( _IQ16mpy(pT, _IQ16(100)) ), _IQtoIQ(t[Check], 24, 16) ) - _IQ16(100);

    if (pPercent < 0)
    {
    if ((v->point_number >= 0) & (v->point_number < 2))
    {
      k = _IQ16div(U[Check - 1] - U[Check], _IQtoIQ(t[Check - 1] - t[Check], 24, 16));
      b = _IQ16div(_IQ16mpyIQX(t[Check - 1], 24, U[Check], 16) - _IQ16mpyIQX(t[Check], 24, U[Check - 1], 16), _IQtoIQ(t[Check - 2] - t[Check], 24, 16));
    }
    else if ((v->point_number >= 2) & (v->point_number <= 5))
    {
      k = _IQ16div(U[Check - 2] - U[Check], _IQtoIQ(t[Check - 2] - t[Check], 24, 16));
      b = _IQ16div(_IQ16mpyIQX(t[Check - 2], 24, U[Check], 16) - _IQ16mpyIQX(t[Check], 24, U[Check - 2], 16), _IQtoIQ(t[Check - 2] - t[Check], 24, 16));
    }
    else if (v->point_number == 6 || v->point_number == 7)
    {
      k = _IQ16div(U[Check - 3] - U[Check], _IQtoIQ(t[Check - 3] - t[Check], 24, 16));
      b = _IQ16div(_IQ16mpyIQX(t[Check - 3], 24, U[Check], 16) - _IQ16mpyIQX(t[Check], 24, U[Check - 3], 16), _IQtoIQ(t[Check - 3] - t[Check], 24, 16));
    }
    else if (v->point_number > 7)
    {
      v-> Status = 0;
      return;
    }
    if (*v->Mode == 2)
    {
      v-> T = _IQ16div(_IQ16mpy(Per, (v-> pUcharge)) - b, k);
    }
    else
    {
      v-> T = _IQ16div(_IQ16mpy(Per, (*v->Urst - v-> pUcharge)) + v-> pUcharge - b, k);
    }
  }
    else
    {
    k = _IQ16div(U[Check - 1] - U[Check], _IQtoIQ(t[Check - 1] - t[Check], 24, 16));
    b = _IQ16div(_IQ16mpyIQX(t[Check - 1], 24, U[Check], 16) - _IQ16mpyIQX(t[Check], 24, U[Check - 1], 16), _IQtoIQ(t[Check - 1] - t[Check], 24, 16));
    if (*v->Mode == 2)
    {
      v-> T = _IQ16div(_IQ16mpy(Per, (v-> pUcharge)) - b, k);
    }
    else
    {
      v-> T = _IQ16div(_IQ16mpy(Per, (*v->Urst - v-> pUcharge)) + v-> pUcharge - b, k);
    }
    }

    v-> Percent = _IQ16div( ( _IQ16mpy(v-> T, _IQ16(100)) ), _IQtoIQ(t[Check], 24, 16) ) - _IQ16(100);
    if (v->Percent > v-> Max_percent || v->Percent < v-> Min_percent)
    {
      if (v->point_number != 0)
      {
        v-> Alarm = 1;
      }
    }
}


static void U_Remember(BLOCK_STRUCT *v, int U_Number)
{
  long *U = &v->U1;
  U[U_Number] = *v->Ucharge;
}

static void Normal(BLOCK_STRUCT *v)
{
  v-> Status = 1;

  v->t1 = _IQ24rsmpy(_IQ24(0.2),_IQtoIQ(*v-> RC, 16, 24));
  v->t2 = _IQ24rsmpy(_IQ24(0.4), _IQtoIQ(*v-> RC, 16, 24));
  v->t3 = _IQ24rsmpy(_IQ24(0.6),_IQtoIQ(*v-> RC, 16, 24));
  v->t4 = _IQ24rsmpy(_IQ24(0.8),_IQtoIQ(*v-> RC, 16, 24));
  v->t5 = _IQtoIQ(*v-> RC, 16, 24);
  v->t6 = _IQ24rsmpy(_IQ24(1.33), _IQtoIQ(*v-> RC, 16, 24));
  v->t7 = _IQ24rsmpy(_IQ24(1.66), _IQtoIQ(*v-> RC, 16, 24));
  v->t8 = _IQ24rsmpy(_IQ24(2),_IQtoIQ(*v-> RC, 16, 24));
  v->t9 = _IQ24rsmpy(_IQ24(2.5),_IQtoIQ(*v-> RC, 16, 24));
  v->t10 = _IQ24rsmpy(_IQ24(3),_IQtoIQ(*v-> RC, 16, 24));
  v->timer += v->Sampletime;


  if(v->timer > v->t10 + _IQ24(1))
  {
    v->timer = 0;
  }

  switch (v->point_number)
  {
    case 0:
    if (v->timer >= v->t1)
    {
      U_Remember(v, 0);
      U_Check(v, 0);
      v->point_number++;
    }
    break;
    case 1:
    if (v->timer >= v->t2)
    {
      U_Remember(v, 1);
      U_Check(v, 1);
      v->point_number++;
    }
    break;
    case 2:
    if (v->timer >= v->t3)
    {
      U_Remember(v, 2);
      U_Check(v, 2);
      v->point_number++;
    }
    break;
    case 3:
    if (v->timer >= v->t4)
    {
      U_Remember(v, 3);
      U_Check(v, 3);
      v->point_number++;
    }
    break;
    case 4:
    if (v->timer >= v->t5)
    {
      U_Remember(v, 4);
      U_Check(v, 4);
      v->point_number++;
    }
    break;
    case 5:
    if (v->timer >= v->t6)
    {
      U_Remember(v, 5);
      U_Check(v, 5);
      v->point_number++;
    }
    break;
    case 6:
    if (v->timer >= v->t7)
    {
      U_Remember(v, 6);
      U_Check(v, 6);
      v->point_number++;
    }
    break;
    case 7:
    if (v->timer >= v->t8)
    {
      U_Remember(v, 7);
      U_Check(v, 7);
      v->point_number++;
    }
    break;
    case 8:
    if (v->timer >= v->t9)
    {
      U_Remember(v, 8);
      U_Check(v, 8);
      v->point_number++;
    }
    break;
    case 9:
    if(v->timer >= v->t10)
    {
      U_Remember(v, 9);
      U_Check(v, 9);
      v->point_number ++;
    }
    break;
  }
}


void Init(void)
{

}

void Exec(void)
{
  if (*v->Reset)
  {
    v-> timer = 0;
    v-> point_number = 0;
    v-> T = 0;
    v-> U1 = 0;
    v-> U2 = 0;
    v-> U3 = 0;
    v-> U4 = 0;
    v-> U5 = 0;
    v-> U6 = 0;
    v-> U7 = 0;
    v-> U8 = 0;
    v-> U9 = 0;
    v-> U10 = 0;
    v-> pUcharge = 0;
    return;
  }

  if (*v->Mode != v->pMode)
  {
    v-> U1 = 0;
    v-> U2 = 0;
    v-> U3 = 0;
    v-> U4 = 0;
    v-> U5 = 0;
    v-> U6 = 0;
    v-> U7 = 0;
    v-> U8 = 0;
    v-> U9 = 0;
    v-> U10 = 0;
    v-> timer = 0;
    v-> point_number = 0;
    v-> pUcharge = *v->Ucharge;
    if (*v-> Mode == 1)
    {
      if (*v->Ucharge > _IQ16mpy(_IQ16(0.995),*v->Urst))
      {
        return;
      }
    }
    if (*v-> Mode == 2)
    {
      if (*v->Ucharge < _IQ16mpy(_IQ16(0.001),*v->Urst))
      {
        return;
      }
    }
   }

  if (*v->Mode == 1 || *v->Mode == 2)
  {
    Normal(v);
    if (v-> point_number == 10)
    {
    v-> timer = 0;
    v->Status = 0;
    }
  }
 else
  {
    v-> timer = 0;
    v->Status = 0;
    v-> pUcharge = *v->Ucharge;
  }
    v->pMode = *v-> Mode;
}


