
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  float v_Cos, v_Sin;  //  ������������� �������� ��� �������� ������ �����
  float v_delt;        //  ����� �������� ���������
  float v_piout;      //  ����� ��-����������

  //  ������� �������� � ������������� ��������� �������� ����� ������� sin/cos � beta/alpha �� ����������� ����
  v->Magn =  sqrt(*v->in_alpha * *v->in_alpha + *v->in_beta * *v->in_beta);;
  v_Cos = *v->in_alpha / v->Magn;
  v_Sin = *v->in_beta / v->Magn;
  v_delt= (v->pout_alpha * v_Sin) - (v->pout_beta * v_Cos);
  v->pout_alpha = v->out_alpha;
  v->pout_beta = v->out_beta;

  // �� ��������� delt->Theta
  v->Ui = v->Up + (v->kp * v_delt / v->f_vf);
  if (v->Ui > v->f_delt)   v->Ui = v->f_delt;
  if (v->Ui < -(v->f_delt))  v->Ui = -v->f_delt;
  v_piout = v_delt * v->kp + v->Ui;
  v->Up = v->Ui;

  if (v_piout > v->f_delt)   v_piout = v->f_delt;
  if (v_piout < -(v->f_delt))  v_piout = -v->f_delt;

  if (v->Thetap > 6.2831853) v->Thetap -= 6.2831853;
  if (v->Thetap < 0) v->Thetap += 6.2831853;
  v->out_alpha = cos(v->Thetap);
  v->out_beta  = sin(v->Thetap);
  v->out_theta = v->Thetap;
  v->Freq = v->f_basic + v_piout;
  v->delt = v_delt;

  // ����������� ���������� ������������� � ���. ���������� Thetap

  if ((short)*v->enable)
  {} else {
    v_piout=0;
    v->Up = 0;
    v->Ui = 0;
    v->Uerr=0;
  }

  if ((short)*v->phase_RST)
  {
    v->Thetap = *v->phase;
  } else {
      v->Thetap += ((v->f_basic + v_piout)* v->Td);
  }


}

