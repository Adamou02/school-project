import { ComponentFixture, TestBed } from '@angular/core/testing';
import { FormsModule } from '@angular/forms';

import { ProfilInputsComponent } from './profil-inputs.component';

describe('ProfilInputsComponent', () => {
  let component: ProfilInputsComponent;
  let fixture: ComponentFixture<ProfilInputsComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [FormsModule],
      declarations: [ProfilInputsComponent]
    });
    fixture = TestBed.createComponent(ProfilInputsComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
