import { ComponentFixture, TestBed } from '@angular/core/testing';
import { HttpClientModule } from '@angular/common/http';
import { FormsModule } from '@angular/forms';

import { DirectoryContentComponent } from './directory-content.component'; 
import { DirectoryComponent } from '../directory/directory.component';

describe('DirectoryContentComponent', () => {
  let component: DirectoryContentComponent;
  let fixture: ComponentFixture<DirectoryContentComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [HttpClientModule, FormsModule],
      declarations: [DirectoryContentComponent, DirectoryComponent]
    });
    fixture = TestBed.createComponent(DirectoryContentComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
