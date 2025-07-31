import { ComponentFixture, TestBed } from '@angular/core/testing';
import { HttpClientModule } from '@angular/common/http';
import { FormsModule } from '@angular/forms';

import { ProfilLeftComponent } from './profil-left.component';

describe('ProfilLeftComponent', () => {
  let component: ProfilLeftComponent;
  let fixture: ComponentFixture<ProfilLeftComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [HttpClientModule, FormsModule],
      declarations: [ProfilLeftComponent]
    });
    fixture = TestBed.createComponent(ProfilLeftComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
