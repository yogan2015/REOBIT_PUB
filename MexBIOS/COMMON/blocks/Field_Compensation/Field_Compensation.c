 #define x *v->Theta
 #define ox v->OffsetTheta
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
if (*v->R) { // Reset
v->Id = 0;
return;
}//eof reset

if (x <= _IQ24(0.2) ){//First Comensation function  y= -0,8654*x*x + 0,0318*x
v->Id = _IQ24mpy( _IQ24(-0.8654), _IQ24mpy(x,x))+ _IQ24mpy( _IQ24(0.0318), x);
return;
}//eof First Comensation function

if (x <= _IQ24(0.36)){//Second Comensation function  y= 1,5001x2 - 0,8269x + 0,0762
v->Id = _IQ24mpy( _IQ24(1.5001), _IQ24mpy(x,x))- _IQ24mpy( _IQ24(0.8269), x)+_IQ24(0.0762);
return;
}//eof Second Comensation function

if (x <= _IQ24(0.786667) ){//Third Comensation function  y = -0,8674x2 + 1,0264x - 0,2863
v->Id = _IQ24mpy( _IQ24(-0.8674), _IQ24mpy(x,x))+ _IQ24mpy( _IQ24(1.0264), x)-_IQ24(0.2863);
return;
}//eof Third Comensation function

if (x <= _IQ24(0.89333)){//Fourth Comensation function  y = 2,3082x2 - 3,8545x + 1,5862
v->Id = _IQ24mpy( _IQ24(2.3082), _IQ24mpy(x,x))- _IQ24mpy( _IQ24(3.8545), x)+_IQ24(1.5862);
return;
}//eof Fourth Comensation function

//Fith Comensation function  y= -0,8654*x*x + 0,0318*x where x = x-1

v->Id =_IQ24mpy( _IQ24(-0.8654), _IQ24mpy((x-_IQ24(1.00)),(x-_IQ24(1.00))))+ _IQ24mpy( _IQ24(0.0318), (x-_IQ24(1.00)));

return;
//eof Fourth Comensation function



}

