import { ComponentFixture, TestBed } from '@angular/core/testing';
import {MAT_DIALOG_DATA, MatDialogRef} from '@angular/material/dialog';

import { NodeCreationRulesComponent } from './node-creation-rules.component';

describe('NodeCreationRulesComponent', () => {
  let component: NodeCreationRulesComponent;
  let fixture: ComponentFixture<NodeCreationRulesComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [NodeCreationRulesComponent],
      providers: [
        {provide: MatDialogRef, useValue: {}},
        {provide: MAT_DIALOG_DATA, useValue: []},
      ]
    });
    fixture = TestBed.createComponent(NodeCreationRulesComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
