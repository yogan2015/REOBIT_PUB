
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
v->Prom1=*v->Mod1;


if(v->Prom1<v->Vmin){v->DCX=0; v->neg_DCX=1;}
if(v->Prom1>v->Vmax){v->DCX=1; v->neg_DCX=0;}

if(*v->avar==0&&v->DCX==0){v->neg_DCX=0; v->DCX=0;}

}

