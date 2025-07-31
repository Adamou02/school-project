import { TestBed } from '@angular/core/testing';
import { HttpClientModule } from '@angular/common/http';

import { TreeService } from './tree.service';

describe('TreeService', () => {
  let service: TreeService;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [HttpClientModule],
    });
    service = TestBed.inject(TreeService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
