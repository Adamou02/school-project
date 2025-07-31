import { ComponentFixture, TestBed } from '@angular/core/testing';
import {MAT_DIALOG_DATA, MatDialogRef} from '@angular/material/dialog';

import { ShowPrivateCodeComponent } from './show-private-code.component';

describe('ShowPrivateCodeComponent', () => {
  let component: ShowPrivateCodeComponent;
  let fixture: ComponentFixture<ShowPrivateCodeComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ShowPrivateCodeComponent],
      providers: [
        {provide: MatDialogRef, useValue: {}},
        {provide: MAT_DIALOG_DATA, useValue: []},
      ]
    });
    fixture = TestBed.createComponent(ShowPrivateCodeComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
