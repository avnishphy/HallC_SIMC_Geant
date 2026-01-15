{
TCaloEvent* ev=new TCaloEvent();
ev->Print();
TCaloBlock* block=ev->AddBlock(2);
TARSWave* wave=ev->AddWave(128);
wave->GetArray()->RandomFill();
wave->GetArray()->Draw();
ev->Print();
ev->AnalyzeFast();
ev->Print();  
}
