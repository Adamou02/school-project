import { ComponentFixture, TestBed } from '@angular/core/testing';
import { HttpClientTestingModule } from '@angular/common/http/testing';
import {MAT_DIALOG_DATA, MatDialogRef} from '@angular/material/dialog';

import { SpecialSuccessPopupComponent } from './special-success-popup.component';

describe('SpecialSuccessPopupComponent', () => {
  let component: SpecialSuccessPopupComponent;
  let fixture: ComponentFixture<SpecialSuccessPopupComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [SpecialSuccessPopupComponent],
      imports: [HttpClientTestingModule],
      providers: [
        {provide: MatDialogRef, useValue: {}},
        {provide: MAT_DIALOG_DATA, useValue: []},
      ]
    });
    fixture = TestBed.createComponent(SpecialSuccessPopupComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
