
void CV() {

  CV1 = analogRead(CV1in);
  CV1 = constrain(map(CV1, 1024, 0, 0, 4), 0, 3);
  //Serial.println(CV1);
  if (CV1 != CV1p) {
    playMode = CV1;

    change = true;
    CV1p = CV1;
  }

  pot = analogRead(potPin);

  CV2 = analogRead(CV2in);
  CVrange[0] = lastStep;
  potRange[0] = lastStep;

  pot = constrain(map(pot, 0, 1024, 0, potRange[potMode] + 1), 0, potRange[potMode]);
  CV2 = constrain(map(CV2, 1024, 0, 0, CVrange[CVmode] + 1), 0, CVrange[CVmode]);

  //if pot and CV mode are the same, use pot as offset, else use values separately
  if (potMode == CVmode) {
    par = pot + CV2;
    par = constrain(par, 0, CVrange[CVmode]);
    if (par != parp) {
      setParam(CVmode, par);
      change = true;
      parp = par;
    }
  } else {
    if (CV2 != CV2p) {
      setParam(CVmode, CV2);
      change = true;
      CV2p = CV2;
    }

    if (pot != potp) {
      setParam(potMode, pot);
      change = true;
      potp = pot;

    }
  }
}

void setParam(int paramMode, int param) {
  switch (paramMode) {
    case 0:
      // offsets the play head
      clk = param;
      playhead = clk;
      setplayhead();
      break;
    case 1:
      // sets gate length
      gateCV = param;
      break;

    case 2:
      // sets last step in sequence
      lastStep = param;
      break;

    case 3:
      // pauses sequence when gate high
      if (param == 1) {
        pause = true;
        pulse = currentMillis - pw;
      } else {

        if (playhead > lastStep) {
          if (playMode == 0) {
            clk = 0;
          }
          if (playMode == 1) {
            clk = lastStep;
          }
          playhead = clk;
        }

        pause = false;

        pulse = currentMillis - pw;
      }
      break;
    case 4:
      // sets first step in sequence
      firstStep = param;
      break;
  }

}

