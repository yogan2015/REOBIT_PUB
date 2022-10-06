
// Do not initialize inputs!


#define stolbets11(_a_)  ((_a_*2)-1)
#define stolbets12(_a_)   (_a_*2)

#define stolbets1(_a_)  ((_a_*2)-1)
#define stolbets2(_a_)   (_a_*2)

#define INIT 1
#define HAND_MODE 2
#define AUTOMATITH_MODE 3
#define AUTO_MODE 4
#define END 0

#define IN_LOAD_MODE 2
#define OUT_LOAD_MODE 3
#define SHIFT_LOAD_MODE 4
#define NORMAL_MODE 5

#define ENABLE 1
#define DISABLE 0

/*static void Func_Init(BLOCK_STRUCT *v)
{
  switch (v->initialisation)
  {
  case 1:
    if(*v->enable == 1) v->initialisation = 4;


    break;
  case 4:
    if(((v->limit_floors[stolbets1(v->n)])&((1<<(*v->quality+1))-1))==((*v->key_switch)&((1<<(*v->quality+1))-1)))   v->initialisation = 2;
    else v->initialisation = 3;*/
//    v->Out = ((v->limit_floors[stolbets1(v->n)])&((1<<(*v->quality+1))-1))/*==(*v->key_switch&((1<<(*v->quality+1))-1));*/
//  /*  v->Out1 = /*((v->limit_floors[stolbets1(v->n)])&((1<<(*v->quality+1))-1))==*//*(*v->key_switch&((1<<(*v->quality+1))-1));
   /* break;
  case 3:
    v->n++;
    if(v->n > (*v->quality+1))v->n = 1;
    v->initialisation = 4;
    break;
  case 2:
    v->turn_floors = v->limit_floors[stolbets12(v->n)];
    v->c = 1;
    v->initialisation = 0;
    break;
  }

}*/
static void Func_In_Load_Mode(BLOCK_STRUCT *v)
{

}

static void Func_Auto_Mode(BLOCK_STRUCT *v)
{
  switch (v->init_auto)
  {
  case INIT:      //проверка введенных данных
    if(*v->load_mode == IN_LOAD_MODE) v->init_auto = IN_LOAD_MODE;
    else if(*v->load_mode == OUT_LOAD_MODE) v->init_auto = OUT_LOAD_MODE;
    else if(*v->load_mode == SHIFT_LOAD_MODE) v->init_auto = SHIFT_LOAD_MODE;
    else if(*v->load_mode == NORMAL_MODE) v->init_auto = NORMAL_MODE;
    else v->init_auto = END;
    break;
  case IN_LOAD_MODE:
    Func_In_Load_Mode(v);
    break;
  case OUT_LOAD_MODE:

    break;
  case SHIFT_LOAD_MODE:

    break;
  case NORMAL_MODE:

    break;
  case END:

    break;
  }
}

void Init(void)
{

}

void Exec(void)
{
  /*switch (v->c)
  {
  case 0:
    if(v->initialisation == 0) v->initialisation = 1;
    Func_Init(v);
    break;
  case 1:
    v->F1 = v->floors[stolbets11(v->turn_floors)];
    v->F2 = v->floors[stolbets12(v->turn_floors)];
    if(*v->In==0) v->c = 2;
    break;
  case 2:
    if(*v->In!=0)
    {
    v->c = 1;
    v->turn_floors++;
    }
    break;
  }*/
  switch (v->initialisation)
  {
  case INIT:
    if(*v->enable == ENABLE)
    {
    if(*v->control_mode == HAND_MODE) v->initialisation = HAND_MODE;
    else if(*v->control_mode == AUTOMATITH_MODE) v->initialisation = AUTOMATITH_MODE;
    else if(*v->control_mode == AUTO_MODE) v->initialisation = AUTO_MODE;
    else v->initialisation = END;
    }
    break;
  case HAND_MODE:
    v->initialisation = END;
    break;
  case AUTOMATITH_MODE:
    v->initialisation = END;
    break;
  case AUTO_MODE:
    Func_Auto_Mode(v);
    v->initialisation = END;
    break;
  }
 }

