import { ComponentFixture, TestBed } from '@angular/core/testing';
import { HttpClientModule } from '@angular/common/http';
import { FormsModule } from '@angular/forms';

import { ContactsChatComponent } from './contacts-chat.component';

describe('ContactsChatComponent', () => {
  let component: ContactsChatComponent;
  let fixture: ComponentFixture<ContactsChatComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [HttpClientModule, FormsModule],
      declarations: [ContactsChatComponent]
    });
    fixture = TestBed.createComponent(ContactsChatComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
