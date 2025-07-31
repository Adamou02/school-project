import { ComponentFixture, TestBed } from '@angular/core/testing';
import {MAT_DIALOG_DATA, MatDialogRef} from '@angular/material/dialog';

import { ErrorMergeTreePopupComponent } from './error-merge-tree-popup.component';

describe('ErrorMergeTreePopupComponent', () => {
  let component: ErrorMergeTreePopupComponent;
  let fixture: ComponentFixture<ErrorMergeTreePopupComponent>;

  beforeEach(async ()  => {
    await TestBed.configureTestingModule({
      declarations: [ErrorMergeTreePopupComponent],
      providers: [
        {provide: MatDialogRef, useValue: {}},
        {provide: MAT_DIALOG_DATA, useValue: []},
      ]
    });
    fixture = TestBed.createComponent(ErrorMergeTreePopupComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
