
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
 if ((short)*v->R)
 {
 v->Id_Ref_MTPA = 0;
 v->Iq_Ref_MTPA = 0;
 return;
 }
   if (v->Ld < v-> Lq)
   {v->Id_Ref_MTPA = _IQ20div(v->PMflux - _IQ20sqrt(_IQ20mpy(v->PMflux, v->PMflux) +
    _IQ20mpy(_IQ20mpy(_IQ20mpy((v->Lq - v->Ld),(v->Lq - v->Ld)), _IQ20mpy(*v->Is_Ref, *v->Is_Ref)), _IQ20(8.0))),
   _IQ20mpy((v->Lq - v->Ld),_IQ20(4.0)) );}

   if (v->Ld > v-> Lq)
   {v->Id_Ref_MTPA = _IQ20div(v->PMflux + _IQ20sqrt(_IQ20mpy(v->PMflux, v->PMflux) +
    _IQ20mpy(_IQ20mpy(_IQ20mpy((v->Lq - v->Ld),(v->Lq - v->Ld)), _IQ20mpy(*v->Is_Ref, *v->Is_Ref)), _IQ20(8.0))),
   _IQ20mpy((v->Lq - v->Ld),_IQ20(4.0)) );}

   if (v->Ld == v-> Lq)
   {v->Id_Ref_MTPA = _IQ20(0.0);}

   if (*v->Is_Ref >= 0)
   {v->Iq_Ref_MTPA = _IQ20sqrt(_IQ20mpy(*v->Is_Ref, *v->Is_Ref) - _IQ20mpy(v->Id_Ref_MTPA, v->Id_Ref_MTPA));}

   if (*v->Is_Ref < 0)
   {v->Iq_Ref_MTPA = -_IQ20sqrt(_IQ20mpy(*v->Is_Ref, *v->Is_Ref) - _IQ20mpy(v->Id_Ref_MTPA, v->Id_Ref_MTPA));}
}

