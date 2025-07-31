import { ComponentFixture, TestBed } from '@angular/core/testing';
import { HttpClientModule } from '@angular/common/http';

import { ContactsContentComponent } from './contacts-content.component';
import { ContactsChatComponent } from '../contacts-chat/contacts-chat.component';
import { ContactsComponent } from '../contacts/contacts.component';

describe('ContactsContentComponent', () => {
  let component: ContactsContentComponent;
  let fixture: ComponentFixture<ContactsContentComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [HttpClientModule],
      declarations: [ContactsContentComponent, ContactsChatComponent, ContactsComponent]
    });
    fixture = TestBed.createComponent(ContactsContentComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
