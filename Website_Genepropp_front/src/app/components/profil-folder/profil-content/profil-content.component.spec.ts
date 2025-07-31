import { ComponentFixture, TestBed } from '@angular/core/testing';
import { HttpClientModule } from '@angular/common/http';

import { ProfilContentComponent } from './profil-content.component';
import { ProfilLeftComponent } from '../profil-left/profil-left.component';
import { ProfilRigthComponent } from '../profil-rigth/profil-rigth.component';

describe('ProfilContentComponent', () => {
  let component: ProfilContentComponent;
  let fixture: ComponentFixture<ProfilContentComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [HttpClientModule],
      declarations: [ProfilContentComponent, ProfilLeftComponent, ProfilRigthComponent]
    });
    fixture = TestBed.createComponent(ProfilContentComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
