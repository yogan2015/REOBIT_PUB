
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->TZ = (*v->IN_IPM0   << 0)  |
          (*v->IN_IPM3   << 5)  |
          (*v->IN_UNET   << 10) |
          (*v->IN_ULOAD  << 13) |
          (*v->IN_HALT_O << 16) |
          (*v->IN_HALT_E << 22) |
          (*v->IN_MISC   << 28);
  v->ALERT |= v->TZ & *v->MASK;
  if ((short)*v->RST) v->ALERT = 0;
}

