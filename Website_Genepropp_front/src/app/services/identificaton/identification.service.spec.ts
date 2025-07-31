import { TestBed } from '@angular/core/testing';
import { HttpClientModule } from '@angular/common/http';

import { IdentificationService } from './identification.service';

describe('IdentificationService', () => {
  let service: IdentificationService;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [HttpClientModule],
    });
    service = TestBed.inject(IdentificationService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
