import { ComponentFixture, TestBed } from '@angular/core/testing';
import { HttpClientModule } from '@angular/common/http';
import { ActivatedRoute } from '@angular/router';
import { of } from 'rxjs';

import { TreeContentComponent } from './tree-content.component';

describe('TreeContentComponent', () => {
  let component: TreeContentComponent;
  let fixture: ComponentFixture<TreeContentComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [HttpClientModule],
      declarations: [TreeContentComponent],
      providers: [
        {
          provide: ActivatedRoute,
          useValue: { queryParams: of({ treeId: 'yourMockedTreeId' }) }
        }
      ]
    });
    fixture = TestBed.createComponent(TreeContentComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
