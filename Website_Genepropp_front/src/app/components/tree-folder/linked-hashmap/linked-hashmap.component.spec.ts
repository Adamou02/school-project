import { ComponentFixture, TestBed } from '@angular/core/testing';

import { LinkedHashMap } from './linked-hashmap.component';

describe('LinkedHashMap', () => {
  let component: LinkedHashMap<string, number>;
  let fixture: ComponentFixture<LinkedHashMap<string, number>>;

  beforeEach(() => {
    TestBed.configureTestingModule({
      declarations: [LinkedHashMap]
    });
    fixture = TestBed.createComponent<LinkedHashMap<string, number>>(LinkedHashMap);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
