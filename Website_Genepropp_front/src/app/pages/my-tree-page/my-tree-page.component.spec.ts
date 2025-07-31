import { ComponentFixture, TestBed } from '@angular/core/testing';
import { HttpClientModule } from '@angular/common/http';
import { ActivatedRoute, convertToParamMap, RouterModule } from '@angular/router';
import { of } from 'rxjs';

import { MyTreePageComponent } from './my-tree-page.component';
import { NavComponent } from '../../components/nav-folder/nav/nav.component';
import { NavElementComponent } from '../../components/nav-folder/nav-element/nav-element.component';
import { TreeContentComponent } from '../../components/tree-folder/tree-content/tree-content.component';
import { FooterComponent } from '../../components/footer/footer.component';

describe('MyTreePageComponent', () => {
  let component: MyTreePageComponent;
  let fixture: ComponentFixture<MyTreePageComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [HttpClientModule, RouterModule],
      declarations: [MyTreePageComponent, NavComponent, TreeContentComponent, FooterComponent, NavElementComponent],
      providers: [
        {
          provide: ActivatedRoute,
          useValue: {
            paramMap: of(convertToParamMap({})),
          },
        },
      ],
    });
    fixture = TestBed.createComponent(MyTreePageComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
