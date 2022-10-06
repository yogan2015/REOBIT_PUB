
void Init(void)
{
}

void Exec(void)
{
  short i;

  // Initialize the filtered signal
  v->Out = 0;

  // Check gains buffer
  if(!*v->Buf) return;

  for(i = v->Order; i >= 0; i--)
  {
    // Pass the previous demodulated signals
    if (i > 0) (&v->Previous)[i] = (&v->Previous)[i-1];
    // Index zero in the array keeps the current demodulated signal
    else (&v->Previous)[0] = *v->In;

    // Filtering the signals
    v->Out += ((float *)(*v->Buf))[i] * (&v->Previous)[i];
  }
}


