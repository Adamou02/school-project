import { ComponentFixture, TestBed } from '@angular/core/testing';
import { HttpClientModule } from '@angular/common/http';
import { FormsModule } from '@angular/forms';

import { ProfilRigthComponent } from './profil-rigth.component';

describe('ProfilRigthComponent', () => {
  let component: ProfilRigthComponent;
  let fixture: ComponentFixture<ProfilRigthComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [HttpClientModule, FormsModule],
      declarations: [ProfilRigthComponent]
    });
    fixture = TestBed.createComponent(ProfilRigthComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
